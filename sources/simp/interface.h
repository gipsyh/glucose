typedef void simp_solver;

extern simp_solver *simp_solver_new();

extern void simp_solver_delete(simp_solver *solver);

extern int simp_solver_add_var(simp_solver *solver);

extern bool simp_solver_add_clause(simp_solver *solver, int * plits, int nlits);

extern int simp_solver_solve(simp_solver *solver, int * plits, int nlits);

extern unsigned char *simp_solver_read_cex(simp_solver *solver);

extern int simp_solver_nvar(simp_solver *solver);