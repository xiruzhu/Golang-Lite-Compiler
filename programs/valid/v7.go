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
func test(a a) {
  var testing b;
  testing.z = 334444444
  var slicing c;
  slicing = append(slicing, testing)
  return
}

func main(){
	var woo struct{
	_ int
	_ int
	z int
	}
	test(woo);
}