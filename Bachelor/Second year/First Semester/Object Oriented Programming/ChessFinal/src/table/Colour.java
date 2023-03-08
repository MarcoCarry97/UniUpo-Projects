/**
 * Gestisce i colori bianco e nero per gli Element e per gli Square
 */


package table;

public enum Colour {
	WHITE,
	BLACK;

	/**
	 * Converte una stringa in Colour, ritorna sempre un colore
	 * @param s stringa da convertire
	 * @return Colour
	 */
	public static Colour stringToColour (String s) {
		if (s.toUpperCase().equals("WHITE")) return Colour.WHITE;
		else return Colour.BLACK;
	}
	/**
	 * Dato un colore in input restituisce l'altro
	 * @param c colore in input
	 * @return Colour
	 */
	public static Colour reverse (Colour c) {
		if (c.equals(Colour.WHITE)) return Colour.BLACK;
		else return Colour.WHITE;
	}
}