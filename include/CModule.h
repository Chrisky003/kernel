#pragma once

class CModule {
public:
    CModule();
    virtual ~CModule() = 0;
public:
    virtual bool init() = 0;
};