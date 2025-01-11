# Car Assurance Management System

## Overview

This program is a console-based **Car Assurance** management system developped in **C++** that uses a **sorted `std::vector` with merge sort** for efficient storage and retrieval of client records. Each client record includes realistic personal and insurance-related fields, such as name, age, contact information, car value, accident history, license suspensions, and policy type. The system calculates risk, trust scores, and monthly premiums based on these parameters.

## Key Features

1. **Sorted Data Storage**
   - Clients are stored in a **`std::vector`**, maintained in sorted order by `client_id` using **merge sort**.
   - Sorting ensures clients are kept in ascending order by their unique IDs, enabling efficient search operations.

2. **Realistic Client Data**
   - Each client record contains fields such as:
     - Personal details: name, age, phone number, address.
     - Insurance details: policy type (Basic, Premium, Gold), car value.
     - Accident history: number of accidents due to the client, accidents not due to the client.
     - License suspensions count.
   - These fields impact the computation of risk scores, trust scores, and monthly premiums.

3. **Dynamic Calculations**
   - **Risk Score**: Calculated from client details, including car value, accidents, and suspensions.
   - **Trust Score**: Evaluates client reliability based on accident history, suspensions, policy type, and computed risk.
   - **Monthly Premium**: Determined by combining risk and trust scores, policy type, and a base fee.

4. **Data Validation**
   - Inputs are validated to ensure realistic and non-negative values (e.g., client age ≥ 18, non-negative accident counts).

5. **Operations via Console Menu**
   - **Show All Clients**: Displays all clients sorted by `client_id`.
   - **Add New Client**: Prompts user for new client information, ensuring a unique `client_id`.
   - **Retrieve Client**: Searches for and displays details of a client by their ID.
   - **Update Client**: Allows partial updates to a client's details.
   - **Remove Client**: Deletes a client record from the system.
   - **Recompute All Scores**: Recalculates risk, trust scores, and monthly premiums for all clients based on the latest data.

## Building and Running with Visual Studio 2022

Follow these steps to build and run the code in Visual Studio 2022:

1. **Clone or Download the Repository**  
   Ensure you have the following files in a single folder:
     - `incl.h`
     - `struct.cpp`
     - `main.cpp`

2. **Create a New Console Application Project**
   - Open Visual Studio 2022.
   - Select **File > New > Project...**.
   - Choose **Console App** under the **C++** section and click **Next**.
   - Name your project and choose a location, then click **Create**.

3. **Add Existing Files to the Project**
   - In the **Solution Explorer**, right-click on the project name.
   - Choose **Add > Existing Item...**.
   - Navigate to the folder containing the downloaded files.
   - Select `incl.h`, `struct.cpp`, and `main.cpp`, then click **Add**.

4. **Verify Project Settings**
   - Ensure that all three files (`incl.h`, `struct.cpp`, and `main.cpp`) are visible under the project in the **Solution Explorer**.
   - Confirm that the project uses at least the C++11 standard (which is generally the default for Visual Studio 2022).

5. **Build the Project**
   - Click on **Build > Build Solution** in the menu bar, or press `Ctrl+Shift+B`.
   - Check the **Output** window for any compilation errors. All files should compile without errors.

6. **Run the Application**
   - After a successful build, run the program by selecting **Debug > Start Without Debugging** from the menu, or by pressing `Ctrl+F5`.
   - A console window should appear displaying the menu for the Car Assurance Management System.

7. **Interact with the System**
   - Use the console menu to add, retrieve, update, or remove clients, as well as to display all clients or recompute scores.
   - Follow the on-screen prompts to enter the required information.

## Formulas and Calculations

- **Risk Score**: Factors in car value, driver's age, at-fault accidents, license suspensions, and other risk influencers.
- **Trust Score**: Rewards not-at-fault accidents, penalizes at-fault accidents and suspensions, adjusts for policy type, and reduces by half the risk score.
- **Monthly Premium**: Starts with a base fee, increases with higher risk, provides discounts for higher trust scores, and adjusts based on policy type.

**Note**: The formulas used for computation are examples!

## Limitations & Future Enhancements

- **Data Structure Optimization**: While a simple `std::vector` with merge sort is used here, using more advanced data structures or algorithms could improve performance for large datasets.
- **Persistent Storage**: Data is stored in memory only. Future versions could incorporate file/database storage for persistence.
- **Policy Details**: The system uses a simple policy type string. Future enhancements could include more detailed policy plans and coverage levels.
- **More Sophisticated Risk Models**: Incorporate advanced algorithms or machine learning models for risk and trust evaluation.

---
