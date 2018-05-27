# thx

 _   _          
| |_| |__ __  __
| __| '_ \\ \/ /
| |_| | | |>  < 
 \__|_| |_/_/\_\
                
This code arose from discussions that I had with Tom Duff.  It is by no
means any kind of attempt to accurately reproduce the famous THX sound:
it is basically just an implementation of the basic ideas:

	- begin with a number of oscillators more or less randomly
	  tuned
	- over time, let them trend toward their final frequencies
	  which reproduce a (D?) major chord.

I lacked all sorts of information at the time, such as the number of 
oscillators and I didn't even bother to figure out what the timing and
overall volume envelope was.  I cobbled together this code in an afternoon
and never went back to think about it again.   

Feel free to use it for whatever purpose you like.  No warranty expressed
or implied.  If you break it in half, you can keep both halves.
