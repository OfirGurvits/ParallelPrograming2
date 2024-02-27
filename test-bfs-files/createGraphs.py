import networkx as nx
import random
import sys

MIN_GRAPH_NODES = int(sys.argv[1])
MAX_GRAPH_NODES = int(sys.argv[2])
MIN_GRAPH_EDGES = 0
#MAX_GRAPH_EDGES depends on the graph, should not be a constant

def get_random_nodes_count():
    return random.randint(MIN_GRAPH_NODES, MAX_GRAPH_NODES)
def get_random_edges_count(nodeCount):
    maxEdgeCount = nodeCount * (nodeCount - 1) / 2
    return random.randint(MIN_GRAPH_EDGES, maxEdgeCount)

def print_graph(graph):
    print(f"{graph.number_of_nodes()} {graph.number_of_edges()}")
    for edge in graph.edges():
        print(*edge)

def create_graph_clique():
    nodeCount = get_random_nodes_count()
    g = nx.complete_graph(nodeCount)
    return g

def create_graph_empty():
    g = nx.Graph()
    nodeCount = get_random_nodes_count()
    g.add_nodes_from([i for i in range(nodeCount)])
    return g

def create_graph_random():
    g = create_graph_clique()
    nodeCount = g.number_of_nodes()
    edgesCount = get_random_edges_count(nodeCount)
    allEdges = list(g.edges())
    edgesToRemove = random.sample(allEdges, g.number_of_edges() - edgesCount)

    for edge in edgesToRemove:
        g.remove_edge(*edge)
    return g

G = create_graph_random()
print_graph(G)