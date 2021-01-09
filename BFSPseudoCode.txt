Psuedo Code

Put the start vertex on the stack/in the queue
while the stack or queue is not empty, do
take a vertex X from the stack or queue;
	if(X has not been visited)
		mark X visited; 
		generate all neighbors of X;
		for each neighbor Y { 
			if (Y  is not visited) 
				put Y on stack/in queue;

Put the start vertex on the stack/in the queue
while the stack or queue is not empty, do
	take a vertex X from the stack or queue;
	if(X has not been visited)
		mark X visited; 
		generate all neighbors of X;
		for each neighbor Y { 
			if (Y is not in_stack_or_queue)
				mark Y as in_stack_or_queue; 
				put Y on stack/in queue;

Put the start vertex on the stack/in the queue
while the stack or queue is not empty, do
	take a vertex X from the stack or queue;
	if(X has not been visited)
		mark X visited; 
		generate all neighbors of X;								 
		for each neighbor Y
			if (Y reached_from is undefined)
				mark Y reached_from X; 
				put Y on stack/in queue; 