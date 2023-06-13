#pragma once

#include <prim/seadSafeString.h>

namespace al {
    void createStringIfInStack(char const*);
    void createConcatString(char const*,char const*);
    void createFileNameBySuffix(sead::BufferedSafeStringBase<char> *,char const*,char const*);
    void outputValueWithComma(char *,unsigned int,unsigned long,bool,bool);
    void extractString(char *,char const*,unsigned int,unsigned int);
    void searchSubString(char const*,char const*);
    void searchSubString(char const*,char const*,int);
    void extractBaseNameW(sead::BufferedSafeStringBase<char16_t> *,sead::SafeStringBase<char16_t> const&);
    void removeExtensionString(char *,unsigned int,char const*);
    void removeStringFromEnd(char *,unsigned int,char const*,char const*);
    void translateCharacters(char *,char const*,char const*);
    void tryReplaceString(sead::BufferedSafeStringBase<char> *,char const*,char const*);
    void tryReplaceString(sead::BufferedSafeStringBase<char> *,char const*,char const*,char const*);
    void tryReplaceStringNoRecursive(sead::BufferedSafeStringBase<char> *,char const*,char const*,char const*);
    bool isEqualString(char16_t const*,char16_t const*);
    bool isEqualSubString(char const*,char const*);
    bool isEqualSubString(sead::SafeStringBase<char> const&,sead::SafeStringBase<char> const&);
    bool isStartWithString(char const*,char const*);
    bool isEndWithString(char const*,char const*);
    void compareStringIgnoreCase(char const*,char const*);
    void makeUrlEncodeString(char *,unsigned int,char const*);
    void makeUrlDecodeString(char *,unsigned int,char const*);
    void copyString(char *,char const*,unsigned int);
    void copyStringW(char16_t *,char16_t const*,unsigned int);
    bool isInStack(void const*);
    bool isEqualString(char const*,char const*);
    bool isEqualString(sead::SafeStringBase<char> const&,sead::SafeStringBase<char> const&);
    bool isEqualStringCase(char const*,char const*);
    bool isEqualStringCase(sead::SafeStringBase<char> const&,sead::SafeStringBase<char> const&);

    template <s32 L>
    class StringTmp : public sead::FixedSafeString<L> {  // equal to WFormatFixedSafeString
    public:
        StringTmp(const char* format, ...) : sead::FixedSafeString<L>() {
            std::va_list args;
            va_start(args, format);
            this->formatV(format, args);
            va_end(args);
        }
        ~StringTmp() = default;
    };
}