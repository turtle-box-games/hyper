/// @file DestructorSpy.h
/// Utility for detecting if a destructor is called.

#ifndef HYPER_TEST_DESTRUCTOR_SPY_H
#define HYPER_TEST_DESTRUCTOR_SPY_H

/// @brief Detects and reports destructor calls.
/// @example destructor_spy.cpp
///   How to use the spy in tests.
class DestructorSpy {
protected:
    int *_callCount;

public:
    /// @brief Default constructor.
    /// @details Creates a spy with no call count.
    ///   This constructor is required for using the spy in arrays.
    DestructorSpy();

    /// @brief General constructor.
    /// @details Creates a spy referencing a counter to increment.
    /// @param callCount Counter to increment when the destructor is called.
    explicit DestructorSpy(int *callCount);

    /// @brief Destructor.
    /// @details Increments the counter every time this destructor is called.
    virtual ~DestructorSpy();
};

/// @brief Subclass for destructor spy.
/// @details Detects and reports whether the destructor is called for the subclass.
///   If the subclass destructor is called, then the count will be two.
///   If only the base destructor is called, then the count will be one.
class DestructorSpySubclass : public DestructorSpy {
public:
    /// @brief Default constructor.
    /// @details Creates a spy with no call count.
    ///   This constructor is required for using the spy in arrays.
    DestructorSpySubclass();

    /// @brief General constructor.
    /// @details Creates a spy referencing a counter to increment.
    /// @param callCount Counter to increment when the destructor is called.
    explicit DestructorSpySubclass(int *callCount);

    /// @brief Destructor.
    /// @details Increments the counter every time this destructor is called.
    ~DestructorSpySubclass() override;
};

#endif // HYPER_TEST_DESTRUCTOR_SPY_H