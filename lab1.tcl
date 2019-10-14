set ns [new Simulator]
set tf [open lab1.tr w]
$ns trace-all $tf
set nf [open lab1.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns color 1 "red"
$ns color 2 "blue"
$n0 label "source/udp0"
$n1 label "source/udp1"
$n2 label "destination"

$ns duplex-link $n0 $n2 10kb 100ms DropTail
$ns duplex-link $n1 $n2 10kb 100ms DropTail

$ns set queue-limit $n0 $n2 5
$ns set queue-limit $n1 $n2 5

set udp0 [new Agent/UDP]
set udp1 [new Agent/UDP]

$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $udp1

set cbr0 [new Application/Traffic/CBR]
set cbr1 [new Application/Traffic/CBR]

$cbr0 attach-agent $udp0
$cbr1 attach-agent $udp1

set null0 [new Agent/Null]
$ns attach-agent $n2 $null0

$udp0 set class_ 1
$udp1 set class_ 2

$ns connect $udp0 $null0
$ns connect $udp1 $null0

$cbr0 set packetSize_ 500Mb
$cbr1 set packetSize_ 500Mb

$cbr0 set interval_ 0.01
$cbr1 set interval_ 0.01

proc finish {} {
global ns nf tf
$ns flush-trace 
exec nam lab1.nam &
close $tf
close $nf 
exit 0
}

$ns at 0.1 "$cbr0 start"
$ns at 0.1 "$cbr1 start"
$ns at 9.0 "$cbr0 stop"
$ns at 9.0 "$cbr1 stop"
$ns at 10.0 "finish"
$ns run


