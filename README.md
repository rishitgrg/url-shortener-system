# URL Shortener System (C++)

A scalable URL Shortener system designed using C++ and Object-Oriented Programming principles.

## Features
- Base62 encoding for short URL generation
- Hash-based key generation with collision handling
- Custom alias support
- TTL-based expiry for automatic cleanup
- Layered architecture (Encoder, Storage, Service)

## Technologies
- C++
- STL
- OOP concepts

## How to Run
```bash
g++ main.cpp -o url_shortener
./url_shortener
