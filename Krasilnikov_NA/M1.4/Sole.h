typedef enum {SYSTEM_OK = 0, ALLOCATION_ERROR, NOT_DEFINED} ErrorCode;

double *solve_system(int n, double *mos, double epsilon, ErrorCode *error);
