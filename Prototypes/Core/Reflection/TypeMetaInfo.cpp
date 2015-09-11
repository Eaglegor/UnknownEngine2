size_t getNextTypeId()
{
	static int i = 0;
	return i++;
}