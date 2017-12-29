int main()
{
	int e = 0;
	RtlAdjustPrivilege(20, 1, 0, &e);
	RtlSetProcessIsCritical(1, 0, 0);
	ExitProcess();
}