#pragma once
#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>

class GroceryItem {
private:
    std::string m_displayName; // keeps original casing from the file
    std::string m_keyName;     // lowercase version for comparisons
    int m_quantity;

    static std::string ToLower(const std::string& text);

public:
    GroceryItem();                              // default
    explicit GroceryItem(const std::string& name); // starts at quantity 1

    const std::string& GetDisplayName() const;
    const std::string& GetKeyName() const;
    int GetQuantity() const;

    void Increment();
};

#endif