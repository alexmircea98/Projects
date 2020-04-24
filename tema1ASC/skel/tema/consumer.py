"""
This module represents the Consumer.

Computer Systems Architecture Course
Assignment 1
March 2020
"""

from threading import Thread
import time


class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.

        :type carts: List
        :param carts: a list of add and remove operations

        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace

        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available

        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self)
        self.carts = carts
        self.marletplace = marketplace
        self.time = retry_wait_time
        self.my_cart = self.marletplace.new_cart()
        self.name = kwargs['name']

    def run(self):
        for cart in self.carts:
            for com in cart:
                if com['type'] == 'add':
                    for i in range(com['quantity']):
                        while not self.marletplace.add_to_cart(self.my_cart, com['product']):
                            time.sleep(self.time)
                        time.sleep(self.time)
                else:
                    for i in range(com['quantity']):
                        self.marletplace.remove_from_cart(self.my_cart, com['product'])

            for certain in self.marletplace.place_order(self.my_cart):

                print(str(self.name) + " bought " + repr(certain))
            del self.marletplace.carts[self.my_cart][:]
