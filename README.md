# Vehicle Rental Management System

A modular C++ console application for managing vehicle rentals offline.

## Features
- User authentication for admin and customers
- Vehicle management
- Booking and availability checks
- Billing and invoice generation
- Maintenance tracking
- Review system
- Reports and dashboards

## Build
On Windows, install MinGW or use a C++ compiler available in PATH, then run:

```powershell
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o VehicleRentalSystem.exe
```

## Folder Structure
- include/: header files
- src/: implementation files
- data/: text data files
- reports/: generated reports

## Default Admin Credentials
- Username: admin
- Password: admin123

> This is a demo credential only. Change it in a production-style version.
