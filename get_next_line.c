#include "get_next_line.h"

char *get_next_line(int fd)
{
	char *join = NULL,buffer[1],*line = NULL;
	int ret,index,flag = 0;

	if(!(line = malloc(1)) || BUFFER_SIZE < 1)
		return(NULL);
	(line)[0] = '\0';
	while((ret = read(fd,buffer,1))>0)
	{
		if(buffer[0]=='\0' && flag == 0)
		return(line);
		if(buffer[0]=='\n' && flag == 0)
		return("\n");
		else if (buffer[0]=='\n' && flag > 0)
		{
			index = 0;
			while((line)[index])
				index++;
			if(!(join=malloc(index + 2)))
				return(NULL);
			index = 0;
			while((line)[index]!='\0')
			{
				join[index]=(line)[index];
				index++;
			}
			join[index++] = buffer[0];
			join[index++] = '\0';
			free(line);
			line = join;
			break;
		}
		index = 0;
		while((line)[index])
			index++;
		if(!(join = malloc(index + 2)))
			return(NULL);		
		index = 0;
		flag++;
		while((line)[index]!='\0')
		{
			join[index] = (line)[index];
			index++;
		}
		join[index++] = buffer[0];
		join[index++] = '\0';
		free(line);
		line = join;	
	}
return(join);
}
