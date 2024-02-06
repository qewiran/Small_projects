function printTableRow(varargin)
    fprintf(varargin{1},"|");
    fprintf(varargin{1},"%i | ", varargin{2});
    fprintf(varargin{1},"%f | ", varargin{3:length(varargin)-1});    
    fprintf(varargin{1},"%i \n", varargin{length(varargin)});    

end
