# URL Shortener System (C++)

A scalable and extensible URL Shortener system implemented in C++ using Object-Oriented Programming (OOP) and STL.  
The project focuses on clean system design, performance, and scalability.

## Motivation
URL shortening is a common backend problem that involves hashing, fast lookups, collision handling, and expiry.  
This project was built to practice system design fundamentals using C++.

## System Design Overview
The system follows a layered architecture:
- Encoder Layer (Base62 encoding)
- Storage Layer (in-memory datastore)
- Service Layer (business logic)

## Features
- Base62 encoding for compact URLs
- O(1) average-time lookup using hash maps
- Collision handling with fallback strategy
- Custom alias support
- TTL-based expiry for memory management

## Technologies Used
- C++
- STL
- Object-Oriented Programming

## How to Run
```bash
g++ main.cpp -o url_shortener
./url_shortener
