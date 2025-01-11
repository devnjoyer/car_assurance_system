#ifndef INCL_H
#define INCL_H

/* Necessary includes. */
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <vector>
#include <cmath>

/*
   Data structure representing a single client in the car assurance system.
*/
struct Client
{
    int client_id;
    std::string client_name;
    int client_age;
    std::string phone_number;
    std::string address;
    std::string policy_type;    /* e.g. "Basic", "Premium", "Gold" */
    double car_value;           /* Value of the insured car. */
    int nb_accidents_due;       /* Accidents caused by the client. */
    int nb_accidents_not_due;   /* Accidents not caused by the client. */
    int nb_suspensions;         /* Number of license suspensions. */

    double risk_score;          /* Computed based on car_value, age, accidents, etc. */
    double trust_score;         /* Evaluates loyalty/risk. */
    double monthly_premium;     /* Computed from risk_score, trust_score, etc. */
};

extern std::vector<Client> g_clients;

/* == FUNCTION == */

/* Insert (add) a new client to the vector. */
void Add_Client(const Client& new_client);

/* Retrieve a client by ID through a search. */
Client* Retrieve_Client_By_Id(int client_id);

/* Remove a client by ID from the vector. */
bool Remove_Client_By_Id(int client_id);

/* Show all clients in ascending order (merge sort by client_id). */
void Show_All_Clients();

/* Clear all client data. */
void Clear_Data();

/* Computations & Validation. */
double Compute_Risk_Score(const Client& c);
double Compute_Trust_Score(const Client& c);
double Compute_Monthly_Premium(const Client& c);
bool Is_Valid_Client_Data(const Client& c);

/* Recompute fields for entire data set. */
void Recompute_All_Scores();

/* Demo/Utility. */
void Load_Sample_Data();

/* Input Handling. */
int Read_Unique_Id_Input();
int Read_Int_Input(const std::string& prompt);
double Read_Double_Input(const std::string& prompt);
std::string Read_String_Input(const std::string& prompt, bool allow_empty = false);

#endif // INCL_H
