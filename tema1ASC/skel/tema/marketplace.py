"""
This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2020
"""
from threading import Semaphore


class Marketplace:
    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """

    def __init__(self, queue_size_per_producer):
        """
        Constructor

        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """
        self.semprod = []
        self.size = queue_size_per_producer
        self.producers = []
        self.carts = []

    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        """
        # Adauga o lista noua de produse si semafor pt acea lista
        self.producers.append([])
        self.semprod.append(Semaphore(value=self.size))

        return len(self.producers) - 1

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.
        """
        self.producers[producer_id].append(product)

    def new_cart(self):
        """
        Creates a new cart for the consumer

        :returns an int representing the cart_id
        """
        self.carts.append([])

        return len(self.carts) - 1

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again
        """
        find = False
        prod_id = -2
        for idx, producer_queue in enumerate(self.producers, start=0):
            if product in producer_queue:
                producer_queue.remove(product)
                prod_id = idx
                self.semprod[prod_id].release()
                find = True
                break

        if not find:
            return False

        self.carts[cart_id].append([product, prod_id])
        return True

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart
        """
        index = -1
        for idx, item in enumerate(self.carts[cart_id], start=0):
            if product in item:
                self.producers[item[1]].append(product)
                index = idx

        del self.carts[cart_id][index]

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart
        """
        new_cart = []
        for prod in self.carts[cart_id]:
            new_cart.append(prod[0])
        return new_cart
