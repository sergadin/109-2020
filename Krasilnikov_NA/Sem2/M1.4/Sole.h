typedef enum {SYSTEM_OK = 0, NOT_DEFINED} ErrorCode;

void *solve_system(int n, double *mos, double *ca, double epsilon, ErrorCode *error);
