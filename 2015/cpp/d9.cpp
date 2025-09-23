/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "utils.h"
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set>

struct node_t;
struct link_t;
struct node_t
{
	std::string name;
	std::vector<link_t *> links;
};

struct link_t
{
	node_t *s, *t;
	int cost;
};

node_t *find_node(std::map<std::string, node_t *> &nodes, std::string name)
{
	node_t *result;
	if (nodes.find(name) != nodes.end())
	{
		result = nodes[name];
	}
	else
	{
		result = new node_t;
		result->name = name;
		nodes[name] = result;
	}
	return result;
}

void d9()
{
	// file_contents fc = read_entire_file("../../2015/d9_input_test.in");
	// file_contents fc = read_entire_file("../../2015/d9_input.in");
	file_contents fc = read_entire_file("../2015/d9_input.in");
	const char *fc_tmp = fc.mem;
	std::map<std::string, node_t *> nodes;
	std::vector<link_t *> links;
	while (fc_tmp && *fc_tmp != '\0')
	{
		std::string s_name = get_variable(&fc_tmp);
		get_variable(&fc_tmp);
		std::string t_name = get_variable(&fc_tmp);
		int weight = get_number(&fc_tmp);
		node_t *s_node = find_node(nodes, s_name);
		node_t *t_node = find_node(nodes, t_name);

		link_t *l = new link_t;
		link_t *ll = new link_t;
		l->cost = weight;
		l->s = s_node;
		l->t = t_node;
		ll->cost = weight;
		ll->s = t_node;
		ll->t = s_node;

		s_node->links.push_back(l);
		t_node->links.push_back(ll);
		links.push_back(l);
		links.push_back(ll);
	}

	// TODO: Continue from here:
	int result = 0, nodeCount = (int)nodes.size();
	links.pop_back();
	std::set<node_t *> tree;
	auto pq_cmp = [&](const link_t *lh, const link_t *rh)
	{
		// std::cout << "LH Cost " << lh->cost << " RH Cost " << rh->cost << std::endl;
		return lh->cost > rh->cost;
	};
	std::priority_queue<link_t *, std::vector<link_t *>, decltype(pq_cmp)>
		searchSpace(pq_cmp);
	// std::priority_queue<link_t*> searchSpace;
	tree.insert(nodes.begin()->second);
	for (auto &n : tree)
	{
		for (auto &l : n->links)
		{
			searchSpace.push(l);
		}
	}
	while (searchSpace.size() > 0 && tree.size() <= nodes.size())
	{
		auto activeSearch = searchSpace.top();
		searchSpace.pop();

		// NOTE: we are in the tree but our target is not.
		if (tree.find(activeSearch->t) == tree.end())
		{
			result += activeSearch->cost;
			tree.insert(activeSearch->t);
			for (auto &l : activeSearch->t->links)
			{
				if (tree.find(l->t) == tree.end())
					searchSpace.push(l);
			}
		}
	}

	for (auto &l : links)
	{
		std::cout << l->s->name << " -> " << l->t->name << " = " << l->cost << ".. deleted" << std::endl;
		delete l;
	}
	links.clear();

	for (auto &[k, v] : nodes)
	{
		std::cout << "Node: " << v->name << " deleted." << std::endl;
		delete v;
	}
	nodes.clear();

	std::cout << "Ans: " << result << std::endl;
}
