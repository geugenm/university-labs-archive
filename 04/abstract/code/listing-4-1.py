import numpy as np
import matplotlib.pyplot as plt

def lstsq(a, b):
    a, _ = _makearray(a)
    b, wrap = _makearray(b)
    is_1d = b.ndim == 1
    if is_1d:
        b = b[:, newaxis]
    _assert_2d(a, b)
    m, n = a.shape[-2:]
    m2, n_rhs = b.shape[-2:]
    if m != m2:
        raise LinAlgError('Incompatible dimensions')

    t, result_t = _commonType(a, b)
    result_real_t = _realType(result_t)

    if m <= n:
        gufunc = _umath_linalg.lstsq_m
    else:
        gufunc = _umath_linalg.lstsq_n

    signature = 'DDd->Ddid' if isComplexType(t) else 'ddd->ddid'
    extobj = get_linalg_error_extobj(_raise_linalgerror_lstsq)
    if n_rhs == 0:
        # lapack can't handle n_rhs = 0 - so allocate the array one larger in that axis
        b = zeros(b.shape[:-2] + (m, n_rhs + 1), dtype=b.dtype)
    x, resids, rank, s = gufunc(a, b, signature=signature, extobj=extobj)
    if m == 0:
        x[...] = 0
    if n_rhs == 0:
        # remove the item we added
        x = x[..., :n_rhs]
        resids = resids[..., :n_rhs]

    # remove the axis we added
    if is_1d:
        x = x.squeeze(axis=-1)
        # we probably should squeeze resids too, but we can't
        # without breaking compatibility.

    # as documented
    if rank != n or m <= n:
        resids = array([], result_real_t)

    # coerce output arrays
    s = s.astype(result_real_t, copy=False)
    resids = resids.astype(result_real_t, copy=False)
    x = x.astype(result_t, copy=True)  # Copying lets the memory in r_parts be freed
    return wrap(x), wrap(resids), rank, s

def generate_task_data():
    x = np.arange(60, 130, 10)
    y = np.array([0.0148, 0.0124, 0.0102, 0.0085, 0.0071, 0.0059, 0.0051])

    return x, y


def process():
    x, y = generate_task_data()

    # Let's fit the data after we applied the log trick.
    A = np.vstack([x, np.ones(len(x))]).T
    beta, log_alpha = lstsq(A, np.log(y), rcond=None)[0]
    alpha = np.exp(log_alpha)
    print(f'alpha={alpha}, beta={beta}')

    # Let's have a look of the data
    plt.figure(figsize=(10, 8))
    plt.plot(x, y, 'b.')
    plt.plot(x, alpha * np.exp(beta * x), 'r')
    plt.xlabel('t')
    plt.ylabel('u')
    plt.show()


if __name__ == '__main__':
    process()
