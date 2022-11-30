#include "interface.h"
#include "SimpSolver.h"

using namespace Glucose;

simp_solver *simp_solver_new()
{
	SimpSolver *S = new SimpSolver;
	S->setIncrementalMode();
	return S;
}

extern void simp_solver_delete(simp_solver *solver)
{
	delete (Glucose::SimpSolver *)solver;
}

int simp_solver_add_var(simp_solver *solver)
{
	return ((Glucose::SimpSolver *)solver)->newVar();
}

bool simp_solver_add_clause(simp_solver *solver, int *plits, int nlits)
{
	vec<Lit> lits;
	Glucose::SimpSolver *S = (Glucose::SimpSolver *)solver;
	for (int i = 0; i < nlits; i++, plits++) {
		// note: Glucose uses the same var->lit conventiaon as ABC
		while ((*plits) / 2 >= S->nVars())
			S->newVar();
		assert((*plits) / 2 <
		       S->nVars()); // NOTE: since we explicitely use new function bmc_add_var
		Lit p;
		p.x = *plits;
		lits.push(p);
	}
	return S->addClause(lits); // returns 0 if the problem is UNSAT
}

int simp_solver_solve(simp_solver *solver, int *plits, int nlits)
{
	vec<Lit> lits;
	Glucose::SimpSolver *S = (Glucose::SimpSolver *)solver;
	for (int i = 0; i < nlits; i++, plits++) {
		assert((*plits) / 2 <
		       S->nVars()); // NOTE: since we explicitely use new function bmc_add_var
		Lit p;
		p.x = *plits;
		lits.push(p);
	}
	lbool res = S->solveLimited(lits, 0);
	return res == l_True ? 1 : (res == l_False ? -1 : 0);
	;
}

unsigned char *simp_solver_read_cex(simp_solver *solver)
{
	Glucose::SimpSolver *S = (Glucose::SimpSolver *)solver;
	return (unsigned char *)S->model.data;
}

int simp_solver_nvar(simp_solver *solver)
{
	Glucose::SimpSolver *S = (Glucose::SimpSolver *)solver;
	return S->nVars();
}
