function out = norm2d(A)
mn=min(min(A));
mx=max(max(A));
out= (A-mn)/(mx-mn);
end

