BEGIN{
count = 0
}
{
if ( $1 == "c" )
count++;
}
END{
printf("\n the total packet collision : %d\n",count);
}
