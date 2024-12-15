//
// Created by alexa on 15/12/2024.
//
#include "Variant.h"

// Constructores
Variant::Variant(VariantType type) : type(type) {}
Variant::Variant(VariantType type, const std::string& val) : type(type), val(val) {}
Variant::Variant(const ListType& lst) : type(List), list(lst) {}

// Método para representar Variant como string (Lisp-like)
std::string Variant::to_string() const {
    std::ostringstream oss;
    switch (type) {
        case Symbol:
            return val;
        case Number:
            return val;
        case String:
            return "\"" + val + "\"";
        case List:
            oss << "(";
            for (size_t i = 0; i < list.size(); ++i) {
                oss << list[i].to_string();
                if (i < list.size() - 1) oss << " ";
            }
            oss << ")";
            return oss.str();
    }
    return "";
}

// Método para convertir Variant a JSON
std::string Variant::to_json_string() const {
    std::ostringstream oss;
    switch (type) {
        case Symbol:
        case String:
            oss << "\"" << val << "\"";
            break;
        case Number:
            oss << val;
            break;
        case List:
            oss << "[";
            for (size_t i = 0; i < list.size(); ++i) {
                oss << list[i].to_json_string();
                if (i < list.size() - 1) oss << ",";
            }
            oss << "]";
            break;
    }
    return oss.str();
}

// Método para convertir JSON a Variant
Variant Variant::from_json_string(const std::string& json) {
    size_t pos = 0;
    skip_whitespace(json, pos);
    return parse_json(json, pos);
}

// Métodos auxiliares
void Variant::skip_whitespace(const std::string& json, size_t& pos) {
    while (pos < json.size() && isspace(json[pos])) ++pos;
}

std::string Variant::parse_string(const std::string& json, size_t& pos) {
    ++pos; // Saltar la comilla inicial
    std::ostringstream oss;
    while (pos < json.size() && json[pos] != '"') {
        oss << json[pos++];
    }
    if (pos >= json.size() || json[pos] != '"') {
        throw std::invalid_argument("JSON inválido: cadena sin cerrar");
    }
    ++pos; // Saltar la comilla final
    return oss.str();
}

Variant Variant::parse_number(const std::string& json, size_t& pos) {
    size_t start = pos;
    if (json[pos] == '-') ++pos;
    while (pos < json.size() && isdigit(json[pos])) ++pos;
    if (pos < json.size() && json[pos] == '.') { // Decimal
        ++pos;
        while (pos < json.size() && isdigit(json[pos])) ++pos;
    }
    return Variant(Number, json.substr(start, pos - start));
}

Variant Variant::parse_list(const std::string& json, size_t& pos) {
    ++pos; // Saltar '['
    ListType elements;
    skip_whitespace(json, pos);
    while (pos < json.size() && json[pos] != ']') {
        elements.push_back(parse_json(json, pos));
        skip_whitespace(json, pos);
        if (json[pos] == ',') ++pos; // Saltar coma
        skip_whitespace(json, pos);
    }
    if (pos >= json.size() || json[pos] != ']') {
        throw std::invalid_argument("JSON inválido: lista sin cerrar");
    }
    ++pos; // Saltar ']'
    return Variant(elements);
}

Variant Variant::parse_json(const std::string& json, size_t& pos) {
    skip_whitespace(json, pos);

    if (json[pos] == '"') { // Cadena de texto
        return Variant(String, parse_string(json, pos));
    } else if (json[pos] == '[') { // Lista
        return parse_list(json, pos);
    } else if (isdigit(json[pos]) || json[pos] == '-') { // Número
        return parse_number(json, pos);
    } else {
        throw std::invalid_argument("JSON inválido: formato no reconocido");
    }
}
