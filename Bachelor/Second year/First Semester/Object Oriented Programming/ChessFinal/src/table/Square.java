/**
 * Quadrato di una scacchiera
 */


package table;

import chesspieces.Element;

public class Square {
	private Element e;
	/**
	 * Sfondo del quadrato
	 */
	public final Colour c;
	
	/**
	 * Ritorna un quadrato con l'elemento e e il colore c
	 * @param e elemento sul quadrato
	 * @param c colore del quadrato
	 */
	public Square(Element e, Colour c){
		this.e = e;
		this.c = c;
	}
	
	/**
	 * Ritorna l'elemento sul quadrato
	 * @return Element
	 */
	
	public Element getElement() {
		return e;
	}

	/**
	 * Sostituisce l'elemento vecchio con e
	 * @param e nuovo elemento da inserire sul quadrato
	 */
	public void changeElement(Element e) {
		this.e = e;
	}
}
