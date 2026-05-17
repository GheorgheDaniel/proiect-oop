#pragma once
#include <exception>
#include <string>
#include <stdexcept>

class ArchiveException : public std::exception {
    protected:
    std::string message;
    public:
    explicit ArchiveException(const std::string& msj) : message(msj) {}

    const char* what() const noexcept override{
        return message.c_str();
    }
};

class FileMissingE : public ArchiveException{
    public: 
    FileMissingE(const std::string& file) : ArchiveException("Fisier lipsa: " + file) {}
};

class CorruptArchiveE : public ArchiveException{
    public: 
    CorruptArchiveE() : ArchiveException("Fisierul binar este corupt") {}
};
