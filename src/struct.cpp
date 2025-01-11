#include "incl.h"

std::vector<Client> g_clients;

/* == MERGE SORT HELPER DECLARATIONS == */
static void Merge_Sort_Clients(int left, int right);
static void Merge_Clients(int left, int mid, int right);

/* == SEARCH HELPER == */
static int Binary_Search_Client_Id(int client_id);

/* Insert (add) a new client to the vector. */
void Add_Client(const Client& new_client)
{
    if (!Is_Valid_Client_Data(new_client))
    {
        std::cout << "Client data is invalid. Cannot insert.\n";
        return;
    }
    /* Insert into vector. */
    g_clients.push_back(new_client);

    /* Maintain sorted order by merging. */
    Merge_Sort_Clients(0, static_cast<int>(g_clients.size()) - 1);
}

/* Retrieve a client by ID through a search. */
Client* Retrieve_Client_By_Id(int client_id)
{
    if (g_clients.empty()) return nullptr;
    int idx = Binary_Search_Client_Id(client_id);
    if (idx == -1) return nullptr;
    return &g_clients[idx];
}

/* Remove a client by ID from the vector. */
bool Remove_Client_By_Id(int client_id)
{
    if (g_clients.empty()) return false;

    int idx = Binary_Search_Client_Id(client_id);
    if (idx == -1) return false;

    g_clients.erase(g_clients.begin() + idx);
    return true;
}

/* Show all clients in ascending order (merge sort by client_id). */
void Show_All_Clients()
{
    if (g_clients.empty())
    {
        std::cout << "No clients found in the system.\n";
        return;
    }
    /* Ensure data is sorted before displaying. */
    Merge_Sort_Clients(0, static_cast<int>(g_clients.size()) - 1);

    std::cout << "\n===== ALL CLIENTS (Sorted by ID) =====\n";
    for (const auto& c : g_clients)
    {
        std::cout << "ID: " << c.client_id
            << " | Name: " << c.client_name
            << " | Age: " << c.client_age
            << " | Phone: " << c.phone_number
            << " | Address: " << c.address
            << " | Policy: " << c.policy_type
            << " | Car Value: " << c.car_value
            << " | Accidents Due: " << c.nb_accidents_due
            << " | Accidents Not Due: " << c.nb_accidents_not_due
            << " | Suspensions: " << c.nb_suspensions
            << " | Risk: " << c.risk_score
            << " | Trust: " << c.trust_score
            << " | Monthly: " << c.monthly_premium << "\n";
    }
}

/* Clear all client data. */
void Clear_Data()
{
    g_clients.clear();
}

/* Computations & Validation. */

double Compute_Risk_Score(const Client& c)
{
    /*
       - Car value relative to client's age (younger drivers with expensive cars are riskier).
       - Past accidents and suspensions increase risk.
       - Diminishing impact of additional accidents.
    */
    double age_factor = (c.client_age < 25) ? 1.5 : (c.client_age < 35 ? 1.2 : 1.0);
    double value_factor = c.car_value / 10000.0;

    double accidents_penalty = 0.0;
    for (int i = 1; i <= c.nb_accidents_due; ++i)
    {
        accidents_penalty += 10.0 / i;
    }

    double suspension_penalty = 3.0 * c.nb_suspensions;
    double random_factor = (std::rand() % 3); // 0..2

    double total = (age_factor * value_factor)
        + accidents_penalty
        + suspension_penalty
        + random_factor;

    return total;
}

double Compute_Trust_Score(const Client& c)
{
    /*
       - Reward not-at-fault accidents, penalize at-fault accidents and suspensions.
       - Policy bonuses. Deduct based on risk_score.
    */
    double base_trust = 60.0;
    double not_due_bonus = 5.0 * c.nb_accidents_not_due;
    double due_penalty = 15.0 * c.nb_accidents_due;
    double suspension_penalty = 20.0 * c.nb_suspensions;

    double policy_bonus = 0.0;
    if (c.policy_type == "Gold")    policy_bonus = 12.0;
    else if (c.policy_type == "Premium") policy_bonus = 7.0;

    double risk_deduction = c.risk_score / 2.0;

    double score = base_trust + not_due_bonus - due_penalty - suspension_penalty + policy_bonus - risk_deduction;
    if (score < 0.0) score = 0.0;

    return score;
}

double Compute_Monthly_Premium(const Client& c)
{
    /*
       - Base fee plus exponential risk factor, minus trust discount, with policy multiplier.
    */
    double base_premium = 40.0;
    double risk_component = std::exp(c.risk_score / 50.0) * 20.0;
    double trust_discount = (c.trust_score > 70) ? 10.0 : (c.trust_score > 50 ? 5.0 : 0.0);

    double policy_multiplier = 1.0;
    if (c.policy_type == "Premium") policy_multiplier = 1.1;
    else if (c.policy_type == "Gold") policy_multiplier = 1.2;

    double premium = (base_premium + risk_component - trust_discount) * policy_multiplier;
    if (premium < 35.0) premium = 35.0;

    return premium;
}

/* Validate client data input */
bool Is_Valid_Client_Data(const Client& c)
{
    if (c.client_id < 0)
    {
        std::cout << "Error: client_id cannot be negative.\n";
        return false;
    }
    if (c.client_age < 18)
    {
        std::cout << "Error: client_age must be >= 18.\n";
        return false;
    }
    if (c.car_value < 0.0)
    {
        std::cout << "Error: car_value cannot be negative.\n";
        return false;
    }
    if (c.nb_accidents_due < 0 || c.nb_accidents_not_due < 0 || c.nb_suspensions < 0)
    {
        std::cout << "Error: accidents/suspensions cannot be negative.\n";
        return false;
    }
    if (c.client_name.empty())
    {
        std::cout << "Error: client_name cannot be empty.\n";
        return false;
    }
    if (c.phone_number.empty())
    {
        std::cout << "Error: phone_number cannot be empty.\n";
        return false;
    }
    if (c.address.empty())
    {
        std::cout << "Error: address cannot be empty.\n";
        return false;
    }
    if (c.policy_type.empty())
    {
        std::cout << "Error: policy_type cannot be empty.\n";
        return false;
    }
    return true;
}

/* Recompute fields for entire data set. */
void Recompute_All_Scores()
{
    std::cout << "Recomputing all client scores...\n";
    for (auto& cl : g_clients)
    {
        cl.risk_score = Compute_Risk_Score(cl);
        cl.trust_score = Compute_Trust_Score(cl);
        cl.monthly_premium = Compute_Monthly_Premium(cl);
    }
    std::cout << "All client scores updated.\n";
}

/* Demo. */
void Load_Sample_Data()
{
    Clear_Data();

    Client c1{ 100, "Alice Johnson",   25, "0612345678", "123 Maple St",
               "Basic",  8000.0,  2, 1, 0,  0.0, 0.0, 0.0 };
    Client c2{ 150, "Bob Wilson",      40, "0755664433", "456 Oak Ave",
               "Premium", 15000.0, 1, 0, 1, 0.0, 0.0, 0.0 };
    Client c3{ 80,  "Charlie Adams",   30, "0788991122", "789 Pine Rd",
               "Gold",  20000.0,  3, 2, 2,  0.0, 0.0, 0.0 };
    Client c4{ 200, "Diana Roberts",   55, "0755123456", "234 Elm St",
               "Basic",  5000.0,  0, 0, 0,  0.0, 0.0, 0.0 };
    Client c5{ 120, "Evan Harris",     29, "0687654321", "567 Birch Ln",
               "Gold",  12000.0,  1, 2, 0,  0.0, 0.0, 0.0 };

    Add_Client(c1);
    Add_Client(c2);
    Add_Client(c3);
    Add_Client(c4);
    Add_Client(c5);

    Recompute_All_Scores();
}

/* Input Handling. */

int Read_Unique_Id_Input()
{
    while (true)
    {
        int id = Read_Int_Input("Enter client ID (>= 0): ");
        if (id < 0)
        {
            std::cout << "Error: ID cannot be negative.\n";
            continue;
        }
        if (Retrieve_Client_By_Id(id) != nullptr)
        {
            std::cout << "Error: this ID already exists. Try another.\n";
            continue;
        }
        return id;
    }
}

int Read_Int_Input(const std::string& prompt)
{
    while (true)
    {
        std::cout << prompt;
        int value;
        if (std::cin >> value)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else
        {
            std::cout << "Invalid integer input. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double Read_Double_Input(const std::string& prompt)
{
    while (true)
    {
        std::cout << prompt;
        double value;
        if (std::cin >> value)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else
        {
            std::cout << "Invalid numeric input. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string Read_String_Input(const std::string& prompt, bool allow_empty)
{
    while (true)
    {
        std::cout << prompt;
        std::string str;
        std::getline(std::cin, str);

        if (!allow_empty && str.empty())
        {
            std::cout << "Input cannot be empty. Please try again.\n";
            continue;
        }
        return str;
    }
}

/* == MERGE SORT + BINARY SEARCH == */

static void Merge_Clients(int left, int mid, int right)
{
    int size_left = mid - left + 1;
    int size_right = right - mid;

    std::vector<Client> L(size_left), R(size_right);

    for (int i = 0; i < size_left; i++)
        L[i] = g_clients[left + i];
    for (int j = 0; j < size_right; j++)
        R[j] = g_clients[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < size_left && j < size_right)
    {
        if (L[i].client_id <= R[j].client_id)
        {
            g_clients[k] = L[i];
            i++;
        }
        else
        {
            g_clients[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < size_left)
    {
        g_clients[k] = L[i];
        i++; k++;
    }
    while (j < size_right)
    {
        g_clients[k] = R[j];
        j++; k++;
    }
}

static void Merge_Sort_Clients(int left, int right)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    Merge_Sort_Clients(left, mid);
    Merge_Sort_Clients(mid + 1, right);
    Merge_Clients(left, mid, right);
}

static int Binary_Search_Client_Id(int client_id)
{
    if (g_clients.empty()) return -1;
    int left = 0;
    int right = static_cast<int>(g_clients.size()) - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (g_clients[mid].client_id == client_id)
            return mid;
        if (g_clients[mid].client_id < client_id)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
