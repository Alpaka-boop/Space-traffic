# Space-traffic
The Department of Space Exploration requires a system for calculating the duration of space routes in various environments.

## Environments

- **Normal Space:**
  - Spaceships in this environment require impulse engines for movement.

- **Dense Space Nebulae:**
  - Impulse engines are inefficient in this environment, making their use impractical. These nebulae have a vast spatial area, and navigation through them is possible only through specialized subspace channels. To traverse these channels, a ship must have the capability to traverse the channel completely — it cannot be done in two attempts. Special jump engines are required for movement through subspace channels.

- **Nitrogen Particle Nebulae:**
  - Spaceships need impulse engines for movement. Contact with nitrogen particles reduces the efficiency of impulse engines, requiring the use of exponentially accelerating impulse engines for optimal passage through such nebulae.

Each environment may contain its corresponding obstacle.

## Engines

- **Class C Impulse Engine:**
  - Standard impulse engine that provides a constant speed of moderate magnitude with relatively low fuel (active plasma) consumption.

- **Class E Impulse Engine:**
  - Exponentially accelerating impulse engine that yields a speed growing exponentially during the acceleration of the ship by this engine. This behavior requires a higher fuel consumption than the Class C engine.

- **Jump Engine:**
  - There are several classes of jump engines (Alpha, Omega, Gamma), differing in the range of travel through subspace channels and the formula for calculating the consumption of special fuel—graviton matter. Alpha has linear consumption, Omega has logarithmic (~n log n) consumption, and Gamma has quadratic consumption.

Launching impulse engines always consumes a specific amount of fuel.

Fuel prices are set on the Fuel Exchange and are measured in Guild Credits.

## Obstacles

- **Meteoroids and Small Asteroids:**
  - Found in normal space, they cause low damage to ship deflectors. Damage to the ship's hull is calculated based on its strength and the mass-dimensions ratio of the ship to the obstacle.

- **Antimatter Flares:**
  - Encountered in subspace channels. To deflect this obstacle, the ship must be equipped with special photon deflectors. They do not damage the ship's hull, but the impact not deflected by photon deflectors will result in the crew's demise.

- **Cosmo-Whales:**
  - Found in nitrogen particle nebulae as they feed on these particles. They deal critical damage to ship deflectors and can destroy the ship if it lacks deflectors, due to their monstrous size. To avoid contact with cosmo-whales, an anti-nitrogen emitter can be used, masking the signal of nitrogen particles, making the ship's trajectory unattractive to them. They may vary in population density (different collision frequencies for a single obstacle).

## Spaceships

- **Leisure Shuttle:**
  - Simple ship equipped with a Class C impulse engine. It lacks deflectors, has a hull strength of 1, and small mass-dimensions characteristics.

- **Vaclas:**
  - Research ship equipped with a Class E impulse engine and a Gamma-class jump engine. It has Class 1 deflectors, a hull strength of 2, and moderate mass-dimensions characteristics.

- **Meridian:**
  - Mining ship equipped with a Class E impulse engine and an anti-nitrogen emitter. It has Class 2 deflectors, a hull strength of 2, and moderate mass-dimensions characteristics.

- **Stella:**
  - Diplomatic ship equipped with a Class C impulse engine and an Omega-class jump engine. It has Class 1 deflectors, a hull strength of 1, and small mass-dimensions characteristics.

- **Augur:**
  - Combat ship equipped with a Class E impulse engine and an Alpha-class jump engine. It has Class 3 deflectors, a hull strength of 3, and large mass-dimensions characteristics.
 
## Deflectors

- **Class 1:**
  Withstand damage caused by two small asteroids or one meteoroid. After deflecting these obstacles, they deactivate.
- **Class 2:**
  Withstand damage caused by ten small asteroids or three meteoroids. After deflecting these obstacles, they deactivate.
- **Class 3:**
  Withstand damage caused by 40 small asteroids, ten meteoroids, or one cosmo-whale. After deflecting these obstacles, they deactivate.
- **Photon Deflectors:**
  Modification allowing the deflection of three antimatter flares. Can be installed on any class of deflectors.

## Hull Strength Classes

- **Class 1:**
  Withstands damage caused by one small asteroid. Any further damage results in the destruction of the ship.
- **Class 2:**
  Withstands damage caused by five small asteroids or two meteoroids. Any further damage leads to the destruction of the ship.
- **Class 3:**
  Withstands damage caused by 20 small asteroids or five meteoroids. Any further damage results in the destruction of the ship.

## Route

- Consists of several path segments.
- Each path segment includes a distance and an environment.
- Possible outcomes of completing a segment:
    - **Success:**
      Contains the time taken for the route, the fuel consumed on this path.
    - **Ship Loss:**
      Occurs if the jump engine's range is insufficient.
    - **Ship Destruction:**
      The crew's demise.

# Test Cases

- Medium-length route in dense nebulae. Process two ships (`[Theory]`): Leisure Shuttle and Augur. The first lacks jump engines, and the second has insufficient range. Both should not complete the route.
- Antimatter flare in a subspace channel. Process two ships (`[Theory]`): Vaclas and Vaclas with photon deflectors. In the first case, the route should not be completed due to crew loss; in the second case, it should be completed.
- Cosmo-whale in a nitrogen particle nebula. Process three ships (`[Theory]`): Vaclas, Augur, and Meridian. The first is destroyed after collision, the second only loses shields, and the third remains unaffected.
- Short route in normal space. Launch Leisure Shuttle and Vaclas. Since Vaclas has a higher flight cost, the Leisure Shuttle should be more optimal for this route.
- Medium-length route in dense nebulae. Launch Augur and Stella. Since Augur has a shorter possible range for subspace channel traversal, Stella should be chosen.
- Route in nitrogen particle nebulae. Launch Leisure Shuttle and Vaclas. Vaclas should be selected.

