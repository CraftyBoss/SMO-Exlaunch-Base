#pragma once

namespace al {
    class ExecutorListBase {
    private:
        const char* mName;
    public:
        ExecutorListBase(char const*);

        virtual ~ExecutorListBase();
        virtual void executeList() const;
        virtual bool isActive() const;
    };
}