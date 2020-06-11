public class TestReordering {
	private static int x = 0, y = 0;
	private static int a = 0, b = 0;

	public static void main(String[] args) throws Exception {
		for (int i = 0; i < 100000000; i++) {
			synchronized(TestReordering.class) { a = 0; b = 0; x = 0; y = 0; }
			Thread one = new Thread(new Runnable() {
				public void run() {
					a = 1; x = b;
				}
			});
			Thread two = new Thread(new Runnable() {
				public void run() {
					b = 1; y = a;
				}
			});
			one.start();two.start();
			one.join();two.join();
			if (x == 0 && y == 0) {
				System.out.println("GOT IT after " + i + " iterations! x="+x+" y="+y);
				break;
			}
		}
	}
}
