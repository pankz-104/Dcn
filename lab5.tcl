set ns [new Simulator]
set tf [open wireless.tr w]
$ns trace-all $tf
set topo [new Topography]
$topo load_flatgrid 700 700
set nf [open wireless.nam w]
$ns namtrace-all-wireless $nf 700 700

$ns node-config -adhocRouting DSDV\
	         -llType LL\
	         -ifqType Queue/DropTail\
	         -macType Mac/802_11\
	         -ifqLen 50\
	         -phyType Phy/WirelessPhy\
	         -channelType Channel/WirelessChannel\
	         -propType Propagation/TwoRayGround\
	         -antType Antenna/OmniAntenna\
	         -topoInstance $topo\
	         -agentTrace ON\
		 -routerTrace ON
create-god 4

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
$n0 label "tcp0"
$n1 label "sink1"
$n2 label "tcp1"
$n3 label "sink2"

$n0 set X_ 50 
$n0 set y_ 50 
$n0 set Z_ 0
$n1 set X_ 200
$n1 set Y_ 200
$n1 set Z_ 0
$n2 set X_ 400
$n2 set Y_ 400
$n2 set Z_ 0
$n3 set X_ 600
$n3 set Y_ 600
$n3 set Z_ 0

$ns at 0.1 "$n0 setdest 50 50 15"
$ns at 0.1 "$n1 setdest 200 200 25"
$ns at 0.1 "$n2 setdest 400 400 25"
$ns at 0.1 "$n3 setdest 600 600 25"

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp0 $sink1

set tcp1 [new Agent/TCP]
$ns attach-agent $n2 $tcp1 

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1 

set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2
$ns connect $tcp1 $sink2 
$ns at 5 "$ftp0 start"
$ns at 10 "$ftp1 start"

$ns at 100 "$n2 setdest 500 500 25"

proc finish {} {
global ns nf tf 
$ns flush-trace 
exec nam wireless.nam &
close $tf
exit 0
}
$ns at 250 "finish"
$ns run 


