#include "GroceryItem.h"
#include <cctype>

GroceryItem::GroceryItem()
    : m_displayName(""), m_keyName(""), m_quantity(0) {
}

GroceryItem::GroceryItem(const std::string& name)
    : m_displayName(name), m_keyName(ToLower(name)), m_quantity(1) {
}

std::string GroceryItem::ToLower(const std::string& text) {
    std::string result;
    result.reserve(text.size());

    for (char ch : text) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    }
    return result;
}

const std::string& GroceryItem::GetDisplayName() const {
    return m_displayName;
}

const std::string& GroceryItem::GetKeyName() const {
    return m_keyName;
}

int GroceryItem::GetQuantity() const {
    return m_quantity;
}

void GroceryItem::Increment() {
    ++m_quantity;
}