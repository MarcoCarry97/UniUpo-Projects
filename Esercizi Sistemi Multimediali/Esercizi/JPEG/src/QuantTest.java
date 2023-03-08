import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class QuantTest
{
	Quant quant;
	
	void init()
	{
		quant=new Quant("Sample.jpg");
	}

	@Test
	void testExecute()
	{
		init();
		quant.execute();
	}

}
