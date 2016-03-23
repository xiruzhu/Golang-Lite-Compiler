package main

var test = 5;
func test2(){
	'a' | 'b'  //Valid
	'a' << 4   //Valid
	'a' << 'b' //Valid in go since Right is RUNE
	4 >> 'a'   //Valid as well
	'a' & 'a'    //Valid
	4:= 5;
}