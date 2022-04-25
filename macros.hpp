#ifndef CT_ECS_MACROS_H
#define CT_ECS_MACROS_H

#ifdef CT_ECS_BUILDING_TESTS
// Expands to virtual in order to makes possible mocking functions in gmock
#define CT_ECS_SPEC virtual
#else
// Expands to inline in order to keep performance in a non-testing build
#define CT_ECS_SPEC inline
#endif

#endif //CT_ECS_MACROS_H
