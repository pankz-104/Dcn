BEGIN{
pkt = 0;
time = 0;
}
{
if( $1 == "r" && $9 == "1.0" && $10 == "5.0")
{
	pkt = pkt + $6
	time = $2;
}
}
END{
printf("throughput : %f Mbps \n ",(pkt/time)*(8/1000000));
}

