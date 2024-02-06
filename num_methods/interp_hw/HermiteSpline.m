function varargout = HermiteSpline (varargin)
n=varargin{1};
m=varargin{2};
tbl_x=varargin{3};
tbl_y=varargin{4};

if nargin==5
    tbl_dy=varargin{5};
end
if nargin==6
    tbl_d2y=varargin{6};
end

for k=1:n-1
    varargout{k} = Hermite(tbl_x(k:k+1), tbl_y(k:k+1), tbl_dy(k:k+1))
end





