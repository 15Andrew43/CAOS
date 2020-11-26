#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PATH_MAX 4096

int main() 
{
	char buffer[PATH_MAX];
	char program[PATH_MAX];
	fgets(buffer, sizeof(buffer), stdin);
	char* slash_n_pos = strchr(buffer, '\n');
	if (slash_n_pos) {
		*slash_n_pos = '\0';
	}
	if (0==strnlen(buffer, sizeof(buffer))) {
		return 0;
	}
	
	snprintf(program, sizeof(program), "#include <stdio.h>\n#include <stdlib.h>\n#include <unistd.h>\n#include <string.h>\nint main() {int res = %s;printf(\"%%d\n\", res);return 0;}", buffer);
	execlp("gcc", "gcc", program, NULL);
	perror("exec");
	exit(1);
}