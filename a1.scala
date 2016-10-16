import Array._
object test{
	var found:Int = -1
	var cnt:Int = 0
	var arr = ofDim[Int](cnt)
	var key:Int = 0
	def main(args: Array[String]){
		println("Enter the size of the array")
		cnt=Console.readInt
		arr=ofDim[Int](cnt)
		println("Enter the elements in ascending order")
		var i:Int = 0
		for (i<-0 to cnt-1){
			arr(i)=Console.readInt
		}
		println("Enter the element to be searched")
		key=Console.readInt
		found=bin(key,0,cnt-1)
		if(found == -1){
			println("Element not found")
		}
		else{
			println("Element found at "+found)
		}
	}
	def bin(key : Int,low : Int,high : Int):Int = {
		if(low==high){
			return found
		}
		var mid:Int = (low+high)/2
		if(arr(mid) == key){
			found=mid
		}
		else if(arr(mid)>key){
			bin(key,low,mid)
		}
		else{
			bin(key,mid+1,high)
		}
		return found
	}
}
