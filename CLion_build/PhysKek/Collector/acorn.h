#ifndef ACORN_H
#define ACORN_H

#include <stdio.h>
/*------------------------------------------------------------------------
 *                                                  The newest version!
 *
 *  Exception class "Acorn"
 *  Acorn - easy and nicely to throw
 *  Acorn - full range of information will thrown directly "on yor head"
 *
 /------------------------------------------------------------------------*/
#define THROW(ERRCODE, MESSAGE, POINTER)\
    throw new Acorn(ERRCODE, MESSAGE , __PRETTY_FUNCTION__,__FILE__,__LINE__, POINTER)


#define FTHROW(ERRCODE, MESSAGE)\
    throw new Acorn(ERRCODE, MESSAGE , __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr)

enum ERRORS {
    MEMORY_ALLOCATION_ERROR = 0,
    MEMORY_ACCES_ERROR,
    INVALID_ARGUMENT,
    OUT_OF_RANGE,
    LOGIC_ERROR,
    SYNTAX_ERROR,
    QUEUE_OVERFLOW,
    UNKNOWN_ERROR = 42
};

const char* LOG_FILE = "acorn_log.txt";


struct Acorn
{
    enum ERRORS errcode_ = UNKNOWN_ERROR;
    const char* message_;
    const char* function_name_;
    const char* file_name_;
    int line_;
    Acorn* Acorn_pointer_ = nullptr;

    inline Acorn(enum ERRORS errcode,
          const char * message,
          const char *function_name,
          const char* file_name,
          int line,
          Acorn* Acorn_pointer);

    void write_log(const char* LOG_FILE_NAME);

    void write_log();

    void tell_user();
};

inline Acorn::Acorn(enum ERRORS errcode,
             const char * message,
             const char *function_name,
             const char* file_name,
             int line,
             Acorn* Acorn_pointer):
        errcode_(errcode),
        message_(message),
        function_name_(function_name),
        file_name_(file_name),
        line_(line),
        Acorn_pointer_(Acorn_pointer)
{
    write_log(LOG_FILE);
}

void Acorn::write_log(const char *LOG_FILE_NAME)
{
    FILE* log = fopen(LOG_FILE_NAME, "a");

    Acorn* acorn = this;
    while(acorn != nullptr) {
        fprintf(log, "Error in FILE [%s]\n"
                     "in FUNCTION [%s]\n"
                     "in LINE [%d]\n"
                     "Error code is [%d]\n"
                     "Message is [%s] \n",
                     acorn->file_name_,
                     acorn->function_name_,
                     acorn->line_,
                     acorn->errcode_,
                     acorn->message_);

        if (acorn->Acorn_pointer_ != nullptr) {
            fprintf(log, "More Info.....\n\n");
        }
        acorn = acorn->Acorn_pointer_;
    }
}

void Acorn::write_log()
{
    write_log(LOG_FILE);
}

void Acorn::tell_user() {
    Acorn* acorn = this;
    while(acorn != nullptr) {
        printf("Error in FILE [%s]\n"
               "in FUNCTION [%s]\n"
               "in LINE [%d]\n"
               "Error code is [%d]\n"
               "Message is [%s] \n",
               acorn->file_name_,
               acorn->function_name_,
               acorn->line_,
               acorn->errcode_,
               acorn->message_);

        if (acorn->Acorn_pointer_ != nullptr) {
            printf("More Info.....\n\n");
        }
        acorn = acorn->Acorn_pointer_;
    }
}

#endif //ACORN_H
