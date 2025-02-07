# Sim Packages System

## Overview

DSA Semester Project, showcasing the understanding the concepts of the data structures and their importance and usage by implementing the Lists DS in C++ and developing a Sim Packages App like JazzWorld etc. The **Sim Packages System** is a C++ application designed to manage and track SIM card packages. It allows users to browse, subscribe to, and manage different SIM packages while providing authentication and account management features.

## Features

- **Customer Section**: Login, Register and manage their account.
- **Admin Section:** Create, Update and Delete Offers and view users' feedbacks. 
- **SIM Package Management**: Browse, subscribe to, and manage SIM packages.
- **Feedback System**: Allows users to provide feedback.
- **Menu-Based Navigation**: Provides an intuitive user interface through console menus.

## Technologies Used

- **Programming Language**: C++
- **IDE**: Visual Studio (Solution & Project files included)
- **File Handling**: Reads and writes data for package management

## Project Structure

```
Sim Packages System/
│── AccountManager.cpp         # Manages user accounts
│── AuthenticationManager.cpp  # Handles authentication
│── FeedbackManager.cpp        # Processes user feedback
│── Main.cpp                   # Main entry point
│── Menus.cpp                  # User navigation system
│── Package.cpp                # SIM package functionalities
│── PackageManager.cpp         # Handles package management
│── Sim Packages System.sln    # Visual Studio solution file
│── Sim Packages System.vcxproj # Visual Studio project file
│── Single File Version/
│   ├── Sim Packages System.cpp # Standalone version of the program
```

## Setup & Installation

1. Clone the repository:

   ```sh
   git clone https://github.com/yourusername/Sim-Packages-System.git
   ```

2. Open `Sim Packages System.sln` in **Visual Studio**.

3. Exclude all C++ files except Main.cpp from build.\
   (Right click on files in Explorer Menu of VS and Exclude from the Project)

5. Build and run the project.
   
6. For Easy mode, just compile and run Single File Version code.

## How to Use

\*\*Customer Section:\*\*

- **Login/Register**: Authenticate using credentials.
- **Browse Packages**: View available SIM packages.
- **Subscribe/Unsubscribe**: Manage subscriptions.
- **Provide Feedback**: Submit feedback on services.

\*\*Admin Section:\*\*

- Authenticate using `0000` as Password.
- Create, Update, Delete and Display offers.
- Read and Delete Customers' Feedbacks.

## Future Enhancements

- Implement a database for persistent data storage.
- Enhance security with encryption.
- Improve UI with a graphical interface.

## Contributors

- **Muhammad Umer**


