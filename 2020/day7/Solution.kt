package day7

class Solution(input: String) {
    private val bagRegistry = hashMapOf<String, Bag>()

    init {
        input.split("\n").forEach { rule ->
            val bagRelationship = rule.split(" contain ")
            val parentBagName = bagRelationship[0].split(" bags")[0]

            val childBags = when (val childBagInformation = bagRelationship[1]) {
                "no other bags." -> listOf()
                else -> childBagInformation.split(", ").map {
                    val bagNameAndQuantity = it.split(Regex("(?<=[0-9]) | (?=(bag))"))
                    Pair(getOrCreateBag(bagNameAndQuantity[1]), bagNameAndQuantity[0].toInt())
                }
            }

            val parentBag = getOrCreateBag(parentBagName)
            childBags.map {
                it.first.parentBags.add(parentBag)
                parentBag.childBags.add(it)
            }
        }
    }

    val parentsOfShinyGoldBag = getAllParentBagsOf(bagRegistry["shiny gold"]!!, mutableSetOf()).size - 1

    val childrenOfShinyGoldBag = getAllChildrenOf(bagRegistry["shiny gold"]!!) - 1

    private fun getAllParentBagsOf(bag: Bag, previousBags: MutableSet<Bag>): MutableSet<Bag> {
        previousBags.add(bag)
        bag.parentBags.forEach {
            if (!previousBags.contains(it)) {
                previousBags.addAll(getAllParentBagsOf(it, previousBags))
            }
        }
        return previousBags
    }

    private fun getAllChildrenOf(bag: Bag): Int {
        if (bag.childBags.size == 0) return 1
        return bag.childBags.fold(1) { acc, it ->
            acc + it.second * getAllChildrenOf(it.first)
        }
    }

    private fun getOrCreateBag(name: String): Bag {
        val wantedBag = bagRegistry[name]
        return if (wantedBag != null) {
            wantedBag
        } else {
            val newBag = Bag()
            bagRegistry[name] = newBag
            newBag
        }
    }

    class Bag {
        val parentBags = mutableSetOf<Bag>()
        val childBags = mutableSetOf<Pair<Bag, Int>>()
    }
}