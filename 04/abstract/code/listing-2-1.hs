import Data.List ( iterate' )

main :: IO ()
main = print $ solve (\ x -> x * x - 17) ( * 2) 4

-- The solve function is universal for all real types whose values can be compared.
solve = esolve 0.000001

esolve epsilon func deriv x0 = fst . head $ dropWile pred pairs
  where
    pred (xn, xn1) = (abs $ xn - xn1) > epsilon -- The pred function determines whether the required precision is achieved.
    next xn = xn - func xn / deriv xn -- The next function calculates a new approximation.
    iters = iterate' next x0 -- An infinite list of iterations.
    pairs = zip iters (tail iters) -- An infinite list of iteration pairs of the form: [(x0, x1), (x1, x2) ...].
