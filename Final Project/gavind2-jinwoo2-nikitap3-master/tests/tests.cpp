#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"

#include "../safecovid.h"
#include "../airportGraph.h"

safeCovid temp("data/edges.txt");

TEST_CASE("Existence of edges in graph") {
  Graph graph_ = temp.getAirportGraph();
  REQUIRE( graph_.assertEdgeExists("YCU","CTU","1"));
  REQUIRE( graph_.assertEdgeExists("CTU","YCU","1"));

  REQUIRE( graph_.assertEdgeExists("OSS","FRU","1"));
  REQUIRE( graph_.assertEdgeExists("FRU","OSS","1"));

  REQUIRE( graph_.assertEdgeExists("DEN","AIA","1"));

  REQUIRE( graph_.assertEdgeExists("GVA","LUG","1"));
  REQUIRE( graph_.assertEdgeExists("LUG","GVA","1"));

  REQUIRE( graph_.assertEdgeExists("LAU","WIL","1"));
  REQUIRE( graph_.assertEdgeExists("WIL","LAU","1"));

  REQUIRE( graph_.assertEdgeExists("KHV","PEK","1"));
  REQUIRE( graph_.assertEdgeExists("PEK","KHV","1"));

  REQUIRE( graph_.assertEdgeExists("CEK","KZN","1"));
  REQUIRE( graph_.assertEdgeExists("KZN","CEK","1"));

  REQUIRE( graph_.assertEdgeExists("CGB","OPS","1"));
  REQUIRE( graph_.assertEdgeExists("OPS","CGB","1"));

  REQUIRE( graph_.assertEdgeExists("HGH","TYN","1"));
  REQUIRE( graph_.assertEdgeExists("TYN","HGH","1"));

  REQUIRE( graph_.assertEdgeExists("DKR","LPA","1"));
  REQUIRE( graph_.assertEdgeExists("LPA","DKR","1"));

  REQUIRE( graph_.assertEdgeExists("ISB","RUH","1"));
  REQUIRE( graph_.assertEdgeExists("RUH","ISB","1"));
}

TEST_CASE("Edge labels") {
  Graph graph_ = temp.getAirportGraph();
  REQUIRE( graph_.getEdgeLabel("YCU","CTU") == "YCU_CTU");
  REQUIRE( graph_.getEdgeLabel("CTU","YCU") == "CTU_YCU");
  REQUIRE( graph_.getEdgeLabel("CEK","KZN") == "CEK_KZN");
  REQUIRE( graph_.getEdgeLabel("KZN","CEK") == "KZN_CEK");
}

TEST_CASE("BFS function") {
  vector<std::string> bfs_path = temp.getPathBFS("BDJ", "MPL");
  REQUIRE(bfs_path[0] == "MPL");
  REQUIRE(bfs_path[1] == "FCO");
  REQUIRE(bfs_path[2] == "SIN");
  REQUIRE(bfs_path[3] == "JOG");
  REQUIRE(bfs_path[4] == "BDJ");
}

TEST_CASE("BFS landmark function") {
  vector<std::string> landmark_path = temp.getPathLandmarkBFS("NTE", "GYE", "CGK");
  REQUIRE(landmark_path[0] == "NTE");
  REQUIRE(landmark_path[1] == "MAD");
  REQUIRE(landmark_path[2] == "GYE");
  REQUIRE(landmark_path[3] == "MAD");
  REQUIRE(landmark_path[4] == "BKK");
  REQUIRE(landmark_path[5] == "CGK");
}

TEST_CASE("Dijkstra's algorithm: 1") {
  float age = 21;
  temp.setPerson(age);
  vector<std::string> dijkstra_path = temp.getPathDijkstra("ORD", "MNL");
  REQUIRE(dijkstra_path[0] == "MNL");
  REQUIRE(dijkstra_path[1] == "NRT");
  REQUIRE(dijkstra_path[2] == "ORD");
}

TEST_CASE("Dijkstra's algorithm: 2") {
  float age = 21;
  temp.setPerson(age);
  vector<std::string> dijkstra_path = temp.getPathDijkstra("DXB", "KEF");
  REQUIRE(dijkstra_path[0] == "KEF");
  REQUIRE(dijkstra_path[1] == "SFB");
  REQUIRE(dijkstra_path[2] == "FAR");
  REQUIRE(dijkstra_path[3] == "ATL");
  REQUIRE(dijkstra_path[4] == "DXB");
}

TEST_CASE("Dijkstra's Landmark algorithm") {
  float age = 21;
  temp.setPerson(age);
  vector<std::string> dijkstra_path = temp.getPathLandmarkDijkstra("YCU", "JOG", "RUH");
  REQUIRE(dijkstra_path[0] == "YCU");
  REQUIRE(dijkstra_path[1] == "JOG");
  REQUIRE(dijkstra_path[2] == "DPS");
  REQUIRE(dijkstra_path[3] == "ICN");
  REQUIRE(dijkstra_path[4] == "RUH");
}
