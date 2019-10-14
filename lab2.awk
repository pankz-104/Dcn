BEGIN{
tcp = 0;
udp = 0;
}
{
if($1 == "r" && $3 == "2" && $4 == "3" && $5 == "tcp")
tcp++;

if($1 == "r" && $3 == "2" && $4 == "3" && $5 == "cbr")
udp++;
}
END{
printf("the total no of packets sent by tcp : %d \n ",tcp);
printf("the total no of packets received by udp : %d \n ",udp);
}

