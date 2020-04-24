import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Class that implements the channel used by headquarters and space explorers to communicate.
 */
public class CommunicationChannel {



	BlockingQueue<Message> SEChannel = new ArrayBlockingQueue<>(100000);
	BlockingQueue<Message> HQChannel = new ArrayBlockingQueue<>(100000);
	public Set<String> discovered	= new HashSet<>();
	ConcurrentHashMap<String, Message> orderer = new ConcurrentHashMap<String, Message>(10000);
	/**
	 * Creates a {@code CommunicationChannel} object.
	 */
	public CommunicationChannel() {
	}

	/**
	 * Puts a message on the space explorer channel (i.e., where space explorers write to and 
	 * headquarters read from).
	 * 
	 * @param message
	 *            message to be put on the channel
	 */
	public void putMessageSpaceExplorerChannel(Message message) {
		try {
			SEChannel.put(message);
		} catch (InterruptedException e) {}
	}

	/**
	 * Gets a message from the space explorer channel (i.e., where space explorers write to and
	 * headquarters read from).
	 * 
	 * @return message from the space explorer channel
	 */
	public Message getMessageSpaceExplorerChannel() {
			try {
				return SEChannel.take();
			} catch (InterruptedException e) {}

		return null;
	}

	/**
	 * Puts a message on the headquarters channel (i.e., where headquarters write to and 
	 * space explorers read from).
	 * 
	 * @param message
	 *            message to be put on the channel
	 */
	public void putMessageHeadQuarterChannel(Message message) {

		if (message.getData().equals("END") || message.getData().equals("EXIT")){

				try {
					HQChannel.put(message);
				} catch (InterruptedException e) {}

		} else {

			String id = Thread.currentThread().getName();

			if (orderer.putIfAbsent(id, message) != null) {
				Message temp = orderer.get(id);
				orderer.remove(id);
				synchronized (HQChannel) {
					try {
						HQChannel.put(temp);
						HQChannel.put(message);

					} catch (InterruptedException e) {}
				}

				//System.out.println(id);
			}
		}
	}

//	public void putMessageHeadQuarterChannel(Message message) {
//
//		try {
//			HQChannel.put(message);
//		} catch (InterruptedException e) {
//		}
//		//System.out.println(Thread.currentThread().getName());
//	}

	/**
	 * Gets a message from the headquarters channel (i.e., where headquarters write to and
	 * space explorer read from).
	 * 
	 * @return message from the header quarter channel
	 */
	public Message getMessageHeadQuarterChannel() {
		try {
			return HQChannel.take();
		} catch (InterruptedException e) {

		}
		return null;
	}
}
