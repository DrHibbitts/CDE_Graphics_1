function [ a ] = lineSearch( x, a_0, c, tau, p, fHandle, dfHandle )
    j = 1;
    t = -c * p' * dfHandle(x);
    a(1) = a_0;
    while (fHandle(x) - fHandle(x + a(j)*p)) < a(j)*t
        j = j + 1;
        a(j) = tau * a(j-1);
    end
end

