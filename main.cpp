//
// Created by alexa on 13/12/2024.
//
#include <iostream>
#include "Variant.h"

int main() {
    // Crear un Variant y convertirlo a JSON
    Variant v(Variant::ListType{Variant(Number, "42"), Variant(String, "hello")});
    std::cout << "to_string: " << v.to_string() << std::endl;         // "(42 "hello")"
    std::cout << "to_json_string: " << v.to_json_string() << std::endl; // "[42,\"hello\"]"

    // Convertir JSON a Variant
    std::string json = "[42, \"hello\"]";
    Variant parsed = Variant::from_json_string(json);
    std::cout << "Parsed JSON to_string: " << parsed.to_string() << std::endl; // "(42 "hello")"

    return 0;
}
