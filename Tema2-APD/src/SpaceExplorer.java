import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Class for a space explorer.
 */
public class SpaceExplorer extends Thread {


	// termination
	private Integer hashCount;
	private static Set<Integer> discovered;

	// communications
	private CommunicationChannel channel;
	/**
	 * Creates a {@code SpaceExplorer} object.
	 * 
	 * @param hashCount
	 *            number of times that a space explorer repeats the hash operation
	 *            when decoding
	 * @param discovered
	 *            set containing the IDs of the discovered solar systems
	 * @param channel
	 *            communication channel between the space explorers and the
	 *            headquarters
	 */
	public SpaceExplorer(Integer hashCount, Set<Integer> discovered, CommunicationChannel channel) {
		this.hashCount = hashCount;
		this.discovered = discovered;
		this.channel = channel;
	}

	@Override
	public void run() {

		Message msg1;
		Message msg2 = new Message(0,0, "");

		while (true) {

			synchronized (channel.HQChannel){
				msg1 = channel.getMessageHeadQuarterChannel();
				if (msg1.getData().equals("END")){
				continue;
				} else if (msg1.getData().equals("EXIT")){
					return;
				} else {
					msg2 = channel.getMessageHeadQuarterChannel();
				}
			}

			synchronized (channel.discovered){
				if(channel.discovered.contains(msg2.getData())){
					continue;
				}
				channel.discovered.add(msg2.getData());
			}

			synchronized (channel.SEChannel){
				channel.putMessageSpaceExplorerChannel(new Message(msg1.getCurrentSolarSystem(),
						msg2.getCurrentSolarSystem(), encryptMultipleTimes(msg2.getData(), hashCount)));
			}
		}
	}
	
	/**
	 * Applies a hash function to a string for a given number of times (i.e.,
	 * decodes a frequency).
	 * 
	 * @param input
	 *            string to he hashed multiple times
	 * @param count
	 *            number of times that the string is hashed
	 * @return hashed string (i.e., decoded frequency)
	 */
	private String encryptMultipleTimes(String input, Integer count) {
		String hashed = input;
		for (int i = 0; i < count; ++i) {
			hashed = encryptThisString(hashed);
		}

		return hashed;
	}

	/**
	 * Applies a hash function to a string (to be used multiple times when decoding
	 * a frequency).
	 * 
	 * @param input
	 *            string to be hashed
	 * @return hashed string
	 */
	private static String encryptThisString(String input) {
		try {
			MessageDigest md = MessageDigest.getInstance("SHA-256");
			byte[] messageDigest = md.digest(input.getBytes(StandardCharsets.UTF_8));

			// convert to string
			StringBuffer hexString = new StringBuffer();
			for (int i = 0; i < messageDigest.length; i++) {
				String hex = Integer.toHexString(0xff & messageDigest[i]);
				if (hex.length() == 1)
					hexString.append('0');
				hexString.append(hex);
			}
			return hexString.toString();

		} catch (NoSuchAlgorithmException e) {
			throw new RuntimeException(e);
		}
	}
}
