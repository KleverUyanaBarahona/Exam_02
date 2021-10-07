#include "get_next_line.h"

int main(void)
{
	char *line;
	
	line = get_next_line(0);
	while(line)
	{
	printf("%s",line);
	line = get_next_line(0);
	}

return(0);
}
