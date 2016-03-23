package main

type a struct{
  _ int;
  _ int;
  z int;
}

type b struct{
  _ int;
  _ int;
  z int;
}

type c []b;
func test(d c) {
  var testing b;
  testing.z = 334444444
  var slicing c;
  slicing = append(slicing, testing)
  return
}

func main(){
	var woo []b
	test(woo);
}