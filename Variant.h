//
// Created by alexa on 15/12/2024.
//

#ifndef VARIANT_H
#define VARIANT_H

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

// Definición de tipos de datos para Variant
enum VariantType { Symbol, Number, List, String };

class Variant {
public:
    using ListType = std::vector<Variant>;

    // Atributos
    VariantType type;
    std::string val;        // Para símbolos, números y cadenas de texto
    ListType list;          // Para listas

    // Constructores
    Variant(VariantType type = Symbol);
    Variant(VariantType type, const std::string& val);
    Variant(const ListType& lst);

    // Métodos principales
    std::string to_string() const;
    std::string to_json_string() const;
    static Variant from_json_string(const std::string& json);

private:
    // Métodos auxiliares para parseo JSON básico
    static void skip_whitespace(const std::string& json, size_t& pos);
    static std::string parse_string(const std::string& json, size_t& pos);
    static Variant parse_number(const std::string& json, size_t& pos);
    static Variant parse_list(const std::string& json, size_t& pos);
    static Variant parse_json(const std::string& json, size_t& pos);
};

#endif //VARIANT_H
