# automaticBandAdjuster
Band adjuster for $^{135}$Pr nucleus

## Project description
Find the optimal constant $const.$ in the expression $$E'=E-const.$$ so that the RMS of the $^{135}$Pr energy sets is minimal.
The constant is used for adjusting the experimental bands (both wobbling and yrast) by subtracting or incrementing the energy states in a certain region that the program finds *unoptimized*.
 
 * Construct a stack of RMS function for an arbitrary set parameters and adjustment constant -> `std::vector<T> RMS_stack`. 
 * Obtain a set of parameters $X=\{A_1,A_2,A_3,\theta\}$ and a value for $const.$ which corresponds to the minimum in the RMS stack.
 * Redo the graphical representation of the energies using the original experimental energies.

### Worflow
-----
-> start with the pure experimental energies (**normalized to the first state**)
->get an arbitrary set of parameters $X_k=\{A_1,A_2,A_3,\theta\}$ and compute $E_\text{RMS}=f(E^{exp}_{X_k},E^{th}_{X_k})$ 
-> check where the highest *unoptimized* region exists: 1st half, 2nd half or middle:
-> calculate the normal differences $\Delta_E=E_{th}-E_{exp}$
* if $\Delta \geq 0$ then subtract a constant value from $E_{exp}$
* if $\Delta < 0$ then add a constant value from $E_{exp}$

-> apply the adjustment for the experimental bands  
